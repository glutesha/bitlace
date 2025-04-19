<script lang="ts">
  import { onMount } from 'svelte';
  import { currentTheme, fetchTheme } from '../theme';

  onMount(async () => {
    await fetchTheme();  
  });

  export let lit: boolean = false;
  export let onClick: () => void;
</script>

<button aria-label="pixel" onclick={onClick}>
  {#if lit}
    <div class={`${$currentTheme.color} size-10 rounded-full shadow-lg ${$currentTheme.shadow}`}></div>
  {:else}
    <div class="bg-neutral-400 hover:bg-neutral-500 size-10 rounded-full"></div>
  {/if}
</button>