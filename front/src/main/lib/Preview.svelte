<script lang="ts">
    import { fetchTheme } from '../theme';
    import { onMount } from 'svelte';
    import { load } from '../saves';
    import { deletetool } from '../delete';
    import PreviewPixel from './PreviewPixel.svelte';

    export let display: boolean[][];
    export let id;

    onMount(async () => {
        await fetchTheme();  
    });

</script>

<button onclick={() => load(id)} oncontextmenu={e => e.preventDefault()} class="flex shadow-xs max-h-42.5 touch-none select-none flex-col items-center bg-black gap-1.5 p-[2px] rounded-md" 
    class:animate-jiggle={$deletetool} 
    class:shadow-red-700={$deletetool}>
    
{#each display as row}
    <div class="flex flex-row gap-1.5">
        {#each row as pixel}
            <PreviewPixel
                lit={pixel} 
            />
        {/each}
    </div>
{/each}
</button>