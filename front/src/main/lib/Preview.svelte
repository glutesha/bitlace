<script lang="ts">
    import { fetchTheme } from '../theme';
    import { onMount } from 'svelte';
    import { SIZE } from '../display';
    import PreviewPixel from './PreviewPixel.svelte';

    export const display = Array.from({ length: SIZE }, () => Array.from({ length: SIZE }, () => false));
    export const id: Number = 0;

    onMount(async () => {
        await fetchTheme();  
    });

</script>

<div role="banner" oncontextmenu={e => e.preventDefault()} class="flex flex-1 touch-none select-none flex-col items-center bg-black gap-1 p-[2px] rounded-md">
{#each display as row, rowIndex}
    <div class="flex flex-row gap-1">
        {#each row as pixel, pixelIndex}
            <PreviewPixel
                lit={pixel} 
            />
        {/each}
    </div>
{/each}
</div>